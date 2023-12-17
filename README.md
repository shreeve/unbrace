# unbrace

```unbrace``` is a Ruby gem to expand braces, similar to a file glob.

## Usage

Just call ```String#unbrace``` for any string containing embeded braces to expand.

## Example

```ruby
irb> puts "lawyer_{name,{work,home}_email_{active,inactive},state}".unbrace
lawyer_name
lawyer_work_email_active
lawyer_work_email_inactive
lawyer_home_email_active
lawyer_home_email_inactive
lawyer_state
```

## License

This software is licensed under terms of the MIT License.
