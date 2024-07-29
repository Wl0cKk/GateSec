require 'socket'
require 'digest'
require 'json'

PORT = 10000

udp = UDPSocket.new

udp.setsockopt(Socket::SOL_SOCKET, Socket::SO_BROADCAST, true)
udp.send( { auth: Digest::SHA1.hexdigest(File.readlines('secret.dat')[0]), note: 'testing' }.to_json, 0, '<broadcast>', PORT )
udp.close