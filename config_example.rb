set :run, true # this is use build-in web-server (puma)
# set :server, 'webrick' # for using castom server - webrick, thin, mongrel...
set :port, 8000 # whatever port you prefer
set :bind, '172.31.255.255' # your IP address

MASTER_KEY_HASH = 'SHA1_OF_UID_MASTER_KEY'