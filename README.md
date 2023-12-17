# unbrace

```unbrace``` is a Ruby gem to expand braces, similar to a file glob.

## Usage

Just call ```String#unbrace``` for any string containing embeded braces to expand.

## Example

```shell
irb> puts "lawyer_{name,{work,home}_email_{active,inactive},state}".unbrace
lawyer_name
lawyer_work_email_active
lawyer_work_email_inactive
lawyer_home_email_active
lawyer_home_email_inactive
lawyer_state

irb> puts "~/{Downloads,Pictures}/*.{jpg,gif,png}".unbrace
~/Downloads/*.jpg
~/Downloads/*.gif
~/Downloads/*.png
~/Pictures/*.jpg
~/Pictures/*.gif
~/Pictures/*.png

irb> puts "It{{em,alic}iz,erat}e{d,}, please.".unbrace
Itemized, please.
Itemize, please.
Italicized, please.
Italicize, please.
Iterated, please.
Iterate, please.
```

## Test

```
ruby -runbrace test/test.rb
```

## License

This software is licensed under terms of the MIT License.
