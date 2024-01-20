#!/bin/bash

for ((i = 1; i <= 400; i++)); do

  three_digit_number=$(printf "%03d" "$i")
 
curl -s -k 'https://meexam.vmail.net.in/MUResult' \
  -X POST \
  -H 'User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/119.0' \
  -H 'Accept: */*' \
  -H 'Accept-Language: en-US,en;q=0.5' \
  -H 'Accept-Encoding: gzip, deflate, br' \
  -H 'Content-Type: application/x-www-form-urlencoded; charset=UTF-8' \
  -H 'X-Requested-With: XMLHttpRequest' \
  -H 'Origin: https://meexam.vmail.net.in' \
  -H 'Connection: keep-alive' \
  -H 'Referer: https://meexam.vmail.net.in/MUResult' \
  -H "Cookie: __RequestVerificationToken=CWAJUFnNZyxcOgFkuU8E2UCKMFbC-jc_f-5MCEpEhixWuiLBzF2dLw8CrTz8x2et8uyt-8tDNHUYxcnLUe0xLh1nqfzoaBFUX-wBMRljB7w1" \
  -H 'Sec-Fetch-Dest: empty' \
  -H 'Sec-Fetch-Mode: cors' \
  -H 'Sec-Fetch-Site: same-origin' \
  -H 'TE: trailers' \
  --data-raw "__RequestVerificationToken=6F-A_1FJf_3sh4OIzObYu-GwrznwdKfU609DY2iS5mJ4rV6uau1vFOx7AFgmI9ggLajt1gy2VlGf1GQ0JJ94mAtcIyqWxkBGRBHyNK7fyRw1&course=01&enrollmentNo=2211129$three_digit_number"  |
    pup 'tr td' | pandoc -f html -t plain | awk 'NF' | sed 's/^[[:space:]]*//' 
 echo " "
    # | { read command_output; [[ $command_output == *SURAJ* ]] && echo "$command_output"; }
done
