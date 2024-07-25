require 'sinatra'
require_relative 'config.rb'
require_relative 'access_control.rb'

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
