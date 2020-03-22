#!/bin/sh
# Author: Ryan Flint
#
# Synopsis: ./gradescript.sh [number of messages] [clean up files]
#
# Description: This program generates [number of messages] messages, stores them in tmp_msg, encrypts them, and then decrypts them. Then,
# a 'diff' is performed on tmp_msg and tmp_dec and gradescript success is based on whether the files are different.

# Temporary files
tmp_msg=./tmp-msg.txt
tmp_enc=./encrypted.txt
tmp_dec=./decrypted.txt

rsa_prog=./rsa

# Check for rsa program existence

if [ ! -f ${rsa_prog} ]; then
	echo "Error: ${rsa_prog} does not exist in the current directory" > /dev/stderr
	exit 1
fi

# Arg check
if [ $# -ne 2 ]; then
	echo 'usage: ./gradescript [num messages] [clean up]' > /dev/stderr
	exit 1
fi

rm -f ${tmp_msg} ${tmp_enc} ${tmp_dec}

# Generate the messages
i=0

while [ $i -lt $1 ]; do
	echo $RANDOM >> ${tmp_msg}

	let "i++"
done

# Do the encryption and decryption
echo "encrypt ${tmp_msg}" | ${rsa_prog} > /dev/null

if [ $? -ne 0 ]; then
	echo 'Problem encrypting messages'
	exit 2
fi

echo "decrypt ${tmp_enc}" | ${rsa_prog} > /dev/null

if [ $? -ne 0 ]; then
	echo 'Problem decrypting messages'
	exit 2
fi

# Check if the decryption worked
diff ${tmp_dec} ${tmp_msg}

if [ $? -ne 0 ]; then
	echo "Decryption unsuccessful. Compare ${tmp_msg} and ${tmp_dec} to see what's wrong"
	exit 3
else
	echo 'Decryption of all messages succeeded! Test case passed!'
fi

# Clean up files if we need to

if [ $2 == 'Y' ]; then
	rm -f ${tmp_msg} ${tmp_enc} ${tmp_dec}
fi

exit 0
