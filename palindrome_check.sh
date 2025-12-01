echo "Enter a string: "
read str

len=${#str}
is_palindrome=1
i=0

while [ $i -lt `expr $len / 2` ]
do 
    j=`expr $len - $i - 1` 
    if [ "${str:$i:1}" != "${str:$j:1}" ]; then
        is_palindrome=0
        break
    fi
    i=`expr $i + 1`
done

if [ $is_palindrome -eq 1 ]; then 
    echo "\"$str\" is a palindrome"
else
    echo "\"$str\" is not a palindrome"
fi