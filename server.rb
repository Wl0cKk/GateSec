require 'sinatra'
require 'sqlite3'
require_relative 'config.rb'

db = SQLite3::Database.new 'sec.db'

def allow_access?(db, id, lvl)
    query = "SELECT COUNT(*) FROM staff WHERE card_id = ? AND access_lvl >= ?"
    # access is only possible if the level of the place is lower than or equal to the level of the entering person
    count = db.get_first_value(query, id, lvl)
    return count > 0
end

before do
    content_type :json
end

get '/auth' do
    { access: allow_access?(db, params['id'], params['lvl']) }.to_json
end

