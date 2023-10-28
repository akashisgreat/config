#!/bin/bash

if [[ $# -lt 2 ]]; then
    echo "Usage: $0"
    exit 1
fi

filename="$1"
work="$2" # -c:crop, -z:file sized changed
arg="$2"

filename_only="${filename%.*}"
ext="${filename##*.}"
org_size=$(stat -c %s "$1")

convert_size_in_byts() {
    file_size="$1"
    file_size="${file_size// /}"
    numeric_value="${file_size//[!0-9.]/}"
    unit="${file_size//[0-9.]/}"
    unit="${unit^^}"
    multiplyer="1000"
    case "$unit" in
    "KB") size_in_byts=$(awk "BEGIN { printf \"%.0f\", $numeric_value * $multiplyer }") ;;
    "MB") size_in_byts=$(awk "BEGIN { printf \"%.0f\", $numeric_value * $multiplyer * $multiplyer }") ;;
    "GB") size_in_byts=$(awk "BEGIN { printf \"%.0f\", $numeric_value * $multiplyer * $multiplyer * $multiplyer }") ;;
    *) echo "Invalid file size unit. Please provide a valid unit (KB, MB, GB)." && exit 1 ;;
    esac
    echo "$size_in_byts"
}

change_size() {
    new_size=$(convert_size_in_byts "$3")
    percentage=$(awk "BEGIN { printf \"%.2f\", ($new_size / $org_size) * 100 }")

    if awk -v num="$percentage" 'BEGIN{ exit !(num > 100) }'; then

        percentage=$(awk "BEGIN { print $percentage - 100 }")

        convert -scale $percentage% $1 $2
        echo "large : $percentage%"
    else
        convert -quality $percentage% $1 $2
        echo "lesser : $percentage%"
    fi

}

change_size "$filename_only.$ext" "${filename_only}_resized.$ext" "$arg"

ls -lh "${filename_only}.$ext"
ls -lh "${filename_only}_resized.$ext"