#!/usr/bin/env bash

ROOT_README="README.md"
AUTHOR=$(whoami)
CREATOR="$0"
CREATOR=${CREATOR[*]/\.\//}
TIME_STAMP=$(date "+%m%d%Y - %T")
TITLE="Page Replacement"
NAME="page_replacement"
DESCRIPTION="Calculates FIFO and LRU page replacement algorithms for a given page reference string."


MD_INCLUDES="md/"

add_meta_data() {
  echo -e "\
---
author: $AUTHOR
creator: $CREATOR
date: $TIME_STAMP
name: $NAME
description: $DESCRIPTION
---

# $TITLE

" > $ROOT_README
}

# Files are prefixed with a number to control the order in which they are
# included in the README.md file.
add_md_files() {
  for file in "$MD_INCLUDES"*.md; do
    cat "$file" >> $ROOT_README
  done
}

add_fifo_solution_section() {
  make clean; make # compile once before to exclude compile output

  echo -e "
## Solutions

### FIFO

\`\`\`
$(make test-fifo)
\`\`\`

" >> $ROOT_README
}

add_lru_solution_section() {
  echo -e "
### LRU

\`\`\`
$(make test-lru)
\`\`\`
" >> $ROOT_README
}

add_meta_data
add_md_files
add_fifo_solution_section
add_lru_solution_section
