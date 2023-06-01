#!/usr/bin/env bash

ROOT_README="README.md"
AUTHOR=$(whoami)
CREATOR="$0"
CREATOR=${CREATOR[@]/\.\//}
TIME_STAMP=$(date "+%m%d%Y - %T")


add_meta_data() {
  echo -e "\
---
author:   $AUTHOR
creator:  $CREATOR
date:     $TIME_STAMP
---

# Operating Systems

This is a collection of programs from my OS class.

## Projects
" > $ROOT_README

}

create_project_status_list(){
  # Get a list of all the directories below the src/prog directory
  proj_dirs=$(find src/prog/ -type d)
  # Remove the src/prog directory from the list
  proj_dirs=${proj_dirs[@]/src\/prog\//}
  #echo "$proj_dirs"

  green_light="🟢"
  red_light="🔴"

  for proj_dir in $proj_dirs; do
    # Create an array containing status of each test
    make -C "$proj_dir" test > /dev/null
    if [ $? -eq 0 ]; then
      proj_status+=("$green_light")
    else
      proj_status+=("$red_light")
    fi
  done
}

add_project_table(){
  # Create a list of all the README.md files in the proj directory
  proj_readmes=$(find src/prog -name "README.md")

  echo -e "\
| Name | Description |
| ---- | ----------- |" >> $ROOT_README

  for readme in $proj_readmes; do
    if [ -n "$readme" ]; then
      echo "Adding $readme to $ROOT_README ..."
      # Get the name of the project from the yaml front matter with sed
      front_matter=$(sed -n '/^---$/,/^---$/p' "$readme")

      # Get the name of the project from the yaml front matter with grep
      name=$(echo "$front_matter" | grep -oP '(?<=name: ).*')
      description=$(echo "$front_matter" | grep -oP '(?<=description: ).*')
      echo -e "| [$name]($readme) | $description |" >> $ROOT_README
    fi
  done
}

#proj_status=()
#create_project_status_list
#echo proj_status: ${proj_status[@]}

add_meta_data
add_project_table

