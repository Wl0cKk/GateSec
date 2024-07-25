require 'sinatra'
require 'sqlite3'
require_relative 'config.rb'
require 'thread'

class AccessManager
  def initialize(db_name)
    @db = SQLite3::Database.new(db_name)
  end

  def allow_access(id, lvl, mutex = nil)
    db_exec = ->(id, lvl) {
      query = "SELECT COUNT(*) FROM staff WHERE card_id = ? AND access_lvl >= ?"
      count = @db.get_first_value(query, id, lvl)
      count > 0
    }
    mutex.nil? ? mutex.synchronize { db_exec.(id, lvl) } : db_exec.(id, lvl)
  end

  def add_user(uid, access_lvl, info, mutex = nil)
    db_exec = ->(uid, access_lvl, info) {
      check_query = "SELECT COUNT(*) FROM staff WHERE card_id = ?"
      existing_count = @db.get_first_value(check_query, uid)
      return false if existing_count > 0

      add_query = "INSERT INTO staff (card_id, user_info, access_lvl) VALUES (?, ?, ?)"
      @db.execute(add_query, uid, info, access_lvl)
      true
    }
    if mutex.nil?
      mutex.synchronize { db_exec.(uid, access_lvl, info) }
    else
      db_exec.(uid, access_lvl, info)
    end
  end

  def edit_user(uid, new_access_lvl, new_info, mutex = nil)
    db_exec = ->(uid, new_access_lvl, new_info) {
      existing_user = @db.get_first_row("SELECT * FROM staff WHERE card_id = ?", uid)
      if existing_user
        edit_query = "UPDATE staff SET access_lvl = ?, user_info = ? WHERE card_id = ?"
        @db.execute(edit_query, new_access_lvl, new_info, uid)
        true
      else
        add_query = "INSERT INTO staff (card_id, user_info, access_lvl) VALUES (?, ?, ?)"
        @db.execute(add_query, uid, new_info, new_access_lvl)
        false
      end
    }
    if mutex.nil?
      mutex.synchronize { db_exec.(uid, new_access_lvl, new_info) }
    else
      db_exec.(uid, new_access_lvl, new_info)
    end
  end

  def delete_user(uid, mutex = nil)
    db_exec = ->(uid) {
      delete_query = "DELETE FROM staff WHERE card_id = ?"
      @db.execute(delete_query, uid)
    }
    mutex.nil? ? mutex.synchronize { db_exec.(uid) } : db_exec.(uid)
  end
end

access_manager = AccessManager.new('sec.db')
mutex = Mutex.new

alert = [
    'User successfully added to database!', # 0
    'User might already exist.',            # 1
    'User successfully updated!'            # 2
]

before do
    content_type :json
end

get '/auth' do
    { access: access_manager.allow_access(params['id'], params['lvl'], mutex) }.to_json
end

get '/admin' do
    return { authorized: false, response: 'Invalid key!' }.to_json if params['master_key'] != MASTER_KEY_HASH

    case params['command']
    when 'add'
        status = access_manager.add_user(params['id'], params['lvl'], params['info'], mutex)
        return {
            status: status,
            response: status ? alert[0] : alert[1]
        }.to_json
    when 'edit'
        status = access_manager.edit_user(params['id'], params['lvl'], params['info'], mutex)
        return {
            status: status,
            response: status ? alert[2] : alert[0]
        }.to_json
    when 'delete'
        access_manager.delete_user(params['id'], mutex)
        return { status: true }.to_json
    end
end
