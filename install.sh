if [ ! -d "/usr/local/lib/ARCC" ]; then
    echo "Creating directory ARCC"
    mkdir /usr/local/lib/ARCC
fi

cp -r ARCC/ /usr/local/include
cp ARCC/Debug/libARCC.so /usr/local/lib/ARCC
