require 'sinatra'
require 'sqlite3'
require_relative 'config.rb'
require 'thread'

db = SQLite3::Database.new 'sec.db'
mutex = Mutex.new

def allow_access?(db, id, lvl)
    query = "SELECT COUNT(*) FROM staff WHERE card_id = ? AND access_lvl >= ?"
    count = db.get_first_value(query, id, lvl)
    return count > 0
end

def add_user(db, uid, access_lvl)
    mutex.synchronize do
        check_query = "SELECT COUNT(*) FROM staff WHERE card_id = ?"
        existing_count = db.get_first_value(check_query, uid)
        return false if existing_count > 0
        add_query = "INSERT INTO staff (card_id, access_lvl) VALUES (?, ?)"
        db.execute(add_query, uid, access_lvl)
        return true
    end
end

def edit_user(db, uid, new_access_lvl)
    mutex.synchronize do
        existing_user = db.get_first_value("SELECT * FROM staff WHERE card_id = ?", uid)
        if existing_user
            edit_query = "UPDATE staff SET access_lvl = ? WHERE card_id = ?"
            db.execute(edit_query, new_access_lvl, uid)
            return true
        else
            return false
        end
    end
end

def delete_user(db, uid)
    mutex.synchronize do
        delete_query = "DELETE FROM staff WHERE card_id = ?"
        db.execute(delete_query, uid)
    end
end

before do
    content_type :json
end

get '/auth' do
    { access: allow_access?(db, params['id'], params['lvl']) }.to_json
end

get '/admin' do 
    return { authorized: false, response: 'Invalid key!' }.to_json if params['master_key'] != MASTER_KEY_HASH
    case params['command']
    when 'add'
        status = add_user(db, params['id'], params['lvl'], params['info'])
        return {
            status: status,
            response: status ? 'User successfully added to database!' : 'User might already exist.'
        }.to_json
    when 'edit'
        status = edit_user(db, params['id'], params['lvl'])
        return {
            status: status,
            response: status ? 'User successfully updated!' : 'User does not exist.'
        }.to_json
    when 'delete'
        delete_user(db, params['id'])
        return { status: true }.to_json
    end    
end
