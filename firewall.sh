#!/bin/bash

# get rid of leftover files
if [[ -e all_rules.txt ]]; then
    rm all_rules.txt
fi

if [[ -e all_rules.txt ]]; then
    rm aprivate_rules.txt
fi

if [[ -e temp_group.txt ]]; then
    rm temp_group.txt
fi

if [[ -e temp_group2.txt ]]; then
    rm temp_group2.txt
fi

if [[ -e all_lines.txt ]]; then
    rm all_lines.txt
fi

if [[ -e packets.txt ]]; then
    rm packets.txt
fi

cat > packets.txt
rules="$1"

# get only relevant information to a new file
sed '/^#/d; /^$/d; s/ //g; s/#.*//' $rules > aprivate_rules.txt

# check the rules for every line
while read line; do
	IFS=',' read -r -a chunks <<< "$line"

# append the results of every rule - and only keep doubles
	./firewall.exe "${chunks[0]}" < packets.txt > temp_group2.txt
	./firewall.exe "${chunks[1]}" < packets.txt >> temp_group2.txt
	cat temp_group2.txt | sort | uniq -D | uniq > temp_group.txt
	./firewall.exe "${chunks[2]}" < packets.txt >> temp_group.txt
	cat temp_group.txt | sort | uniq -D | uniq > temp_group2.txt
	./firewall.exe "${chunks[3]}" < packets.txt >> temp_group2.txt
	cat temp_group2.txt | sort | uniq -D | uniq >> all_lines.txt

done < aprivate_rules.txt


sed -i 's/ //g' all_lines.txt 
cat all_lines.txt | sort | uniq
