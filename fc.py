import os
import sys

max_chunk = 1048576

output_file = sys.argv[1]
size = int(sys.argv[2])

with open(output_file, 'wb') as fout:
    written = 0
    count = 0
    while written < size:
        chunk_size = size - written
        if chunk_size > max_chunk:
            chunk_size = max_chunk
        fout.write(os.urandom(chunk_size))
        fout.flush()
        written += chunk_size
        count += 1
        print("Wrote chunk %d" % count)

