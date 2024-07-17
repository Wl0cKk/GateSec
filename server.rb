require 'sinatra'
require 'sqlite3'
require_relative 'config.rb'

before do
    content_type :json
end

get '/:rfid' do |n|
    { access: "false" }.to_json
end
  