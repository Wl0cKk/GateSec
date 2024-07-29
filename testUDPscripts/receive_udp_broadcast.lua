local socket = require("socket")
local json = require("dkjson")
local port = 10000

local udp = socket.udp()
udp:setsockname("0.0.0.0", port)

print("Listening " .. port .. "...")

while true do
    local data, ip = udp:receivefrom()
    -- local msg = json.decode(data)
    print(data)
end
