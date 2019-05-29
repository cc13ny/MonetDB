# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0.  If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.

from __future__ import print_function

import os, sys

total_files = len(sys.argv)
if total_files < 2:
    raise Exception("There is no output file")
if total_files < 3:
    raise Exception("There are no input files")

# The output file will be the first argument
output_file_base = os.path.basename(sys.argv[1])
output_file_split = os.path.splitext(output_file_base)
if len(output_file_split) < 2 or output_file_split[1] != '.h':
    raise Exception("Only .h files are supported for the output file")

sql_h_output_file = open(sys.argv[1], 'w')

# write the C array entry
insert1 = ''.join([
    '/*\n',
    '* This Source Code Form is subject to the terms of the Mozilla Public\n',
    '* License, v. 2.0.  If a copy of the MPL was not distributed with this\n',
    '* file, You can obtain one at http://mozilla.org/MPL/2.0/.\n',
    '*\n',
    '* Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.\n',
    '*/\n',
    '\n',
    '// This file was generated automatically with sql2h.py. Do not edit this file directly.\n',
    'char ', output_file_split[0], '[] = {'])
sql_h_output_file.write(insert1)

file_stat = os.stat(sys.argv[1])
if os.name == 'nt':
    CACHE_SIZE = 512
else:
    CACHE_SIZE = file_stat.st_blksize  # we will set the cache size to the filesystem blocksize

buffer = ['\0'] * CACHE_SIZE
current_output_file_pointer = 0
current_input_file_number = 2

# Iterate over the input files
while current_input_file_number < total_files:
    next_file = sys.argv[current_input_file_number]

    if not os.path.exists(next_file):
        raise Exception(''.join(["File ", next_file, " doesn't exist"]))
    if not os.path.isfile(next_file):
        raise Exception(''.join([next_file, " is not a file"]))

    file_stat = os.stat(next_file)
    if file_stat.st_size > (1 << 29):
        raise Exception(''.join(["File ", next_file, " is too large to process"]))

    # get the file name and extension
    input_file_base = os.path.basename(next_file)
    input_file_split = os.path.splitext(input_file_base)
    if len(input_file_split) < 2 or input_file_split[1] != '.sql':
        raise Exception("Only .sql files are supported as input")

    sql_content_file = open(next_file, 'r')
    sql_content = sql_content_file.read()
    sql_content_file.close()

    i = 0
    cur_state = 0
    endloop = len(sql_content) - 1

    # Let's remove comments from the sql script with a Markov chain :) Bugs might still be there
    # STATES 0 - OK, 1 in # comment, 2 in -- comment, 3 in /* comment, 4 inside whitespaces
    while i < endloop:
        c = sql_content[i]

        if cur_state == 1:
            if c == '\n':
                cur_state = 0
            i += 1
            continue
        elif cur_state == 2:
            if c == '\n':
                cur_state = 0
            i += 1
            continue
        elif cur_state == 3:
            if c == '*' and i + 1 < endloop and sql_content[i + 1] == '/':
                cur_state = 0
                i += 1
            i += 1
            continue
        elif cur_state == 4:
            if c not in (' ', '\t', '\n'):
                cur_state = 0
                continue
            i += 1
            continue

        if c == '#':
            cur_state = 1
            i += 1
            continue
        elif c == '-' and i + 1 < endloop and sql_content[i + 1] == '-':
            cur_state = 2
            i += 2
            continue
        elif c == '/' and i + 1 < endloop and sql_content[i + 1] == '*':
            cur_state = 3
            i += 2
            continue

        if current_output_file_pointer == CACHE_SIZE:
            sql_h_output_file.write("".join(buffer))
            current_output_file_pointer = 0
        buffer[current_output_file_pointer] = str(ord(c))
        current_output_file_pointer += 1
        if current_output_file_pointer == CACHE_SIZE:
            sql_h_output_file.write("".join(buffer))
            current_output_file_pointer = 0
        buffer[current_output_file_pointer] = ','
        current_output_file_pointer += 1

        if c in (' ', '\t', '\n'):
            cur_state = 4  # Trim always
        i += 1

    current_input_file_number += 1

if current_output_file_pointer > 0:
    sql_h_output_file.write("".join(buffer[:current_output_file_pointer]))

# finish C array entry
sql_h_output_file.write("0};\n")
sql_h_output_file.close()
