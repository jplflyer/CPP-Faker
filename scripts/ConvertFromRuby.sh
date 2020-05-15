#!/usr/local/bin/bash
#
# Converts the YAML files from faker-ruby into the JSON we use.
#
# Warning: by default, Faker's original ./en/super_smash_bros.yml has
# an error on the "Windy Hill Zone" line -- trailing garbage that the Python
# YAML parser throws errors on. Manually edit the file and remove the trailing
# whitespace.

INPUT_DIR=""
OUTPUT_DIR="./locales"

while [ -n "$*" ]; do
    arg="$1"
    shift

    case $arg in
    --from)
        INPUT_DIR="$1"
        shift
        ;;

    --to)
        OUTPUT_DIR="$1"
        shift
        ;;

    esac
done

if [ -z "$INPUT_DIR}" ]; then
    echo "No INPUT_DIR."
    exit 0
fi

function yaml2json {
    python -c 'import sys, yaml, json; print(json.dumps(yaml.safe_load(sys.stdin.read()), indent=2, sort_keys=False))'
}

function convert_dir {
    local dir="$1"
    local this_input_dir=${INPUT_DIR}/${dir}
    local this_output_dir=${OUTPUT_DIR}/${dir}
    local fname
    local outname

    if [ ! -d ${this_output_dir} ]; then
        mkdir -p ${this_output_dir}
    fi

    ls -1 ${this_input_dir} | (
        while read fname; do
            if [ -f $this_input_dir/$fname ]; then
                if [[ $fname == **.yml ]]; then
                    outname=`echo $fname | sed 's/.yml/.json/' | sed 's/-/_/g'`
                    echo "$dir/$fname"
                    yaml2json < $this_input_dir/$fname > $this_output_dir/$outname
                fi
            elif [ -d $this_input_dir/$fname ]; then
                convert_dir $dir/$fname
            fi
        done
    )
}

convert_dir "."
