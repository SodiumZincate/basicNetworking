if [ -z "$1" ]; then
	echo "Usage: $0 <database>"
	exit 1
fi

file="./uploads/"
file+="$1"
file+=".db"

if [ -e "$file" ]; then
	echo "File already exists"
else
	g++ database.cpp -o database -l sqlite3 && ./database "$1"
	# g++ uploader.cpp -o uploader && ./uploader "$file"
fi
# g++ client.cpp -o client -l sqlite3 && ./client delete

rm database > /dev/null 2>&1
rm client > /dev/null 2>&1