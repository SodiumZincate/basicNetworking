if [ -z "$1" ]; then
	echo "Usage: $0 <client_req>"
	exit 1
fi

file="./uploads/leaguedata.db"

if [ -e "$file" ]; then
	echo "File already exists"
else
	g++ database.cpp -o database -lsqlite3
	./database
fi

g++ client.cpp -o client -lsqlite3
./client $1

rm database > /dev/null 2>&1
rm client > /dev/null 2>&1