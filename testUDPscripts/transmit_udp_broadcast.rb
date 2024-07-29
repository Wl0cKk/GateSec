require 'socket'
require 'json'

local_ip = -> { Socket.ip_address_list.find(&:ipv4_private?).ip_address }
PORT = 10000

udp = UDPSocket.new
udp.setsockopt(Socket::SOL_SOCKET, Socket::SO_BROADCAST, true)

loop do
  udp.send( { ip: local_ip.call, note: 'testing' }.to_json, 0, '<broadcast>', PORT )
  sleep(5)
end
