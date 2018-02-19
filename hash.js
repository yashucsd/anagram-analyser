function hash(str) {
	int hash = 11;
    int strLen = str.length();
    for( int i = 0; i < strLen; i++ ) {
           hash = hash * 37 + str[i];
    }
	console.log(hash);
}