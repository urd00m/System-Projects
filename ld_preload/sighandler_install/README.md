# Instructions 
run `make test`

# Notes
The signal handler doens't actually fix anything in libsig_install.so, since it can't modify the context which means nothing it does will change anything. So need to add in the context to fix the divide by zero error

