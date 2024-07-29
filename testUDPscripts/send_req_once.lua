local socket = require("socket")
local json = require("dkjson")

local udp = socket.udp()
udp:setpeername("0.0.0.0", 10000)

udp:send(json.encode({ auth = 'password', note = 'testing' }))
udp:close()
