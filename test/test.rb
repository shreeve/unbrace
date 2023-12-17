require "unbrace"

strs = <<'EOS'
1{2,{3,4}5{6,7},8}{9,{a,b,c},d}e
a{b,{c,d}_e_{f,g},h}{i,{j,k,l},m}n
lawyer_{name,{work,home}_email_{active,inactive},state}
~/{Downloads,Pictures}/*.{jpg,gif,png}
It{{em,alic}iz,erat}e{d,}, please.
{,{,gotta have{ ,\, again\, }}more }cowbell!
{}} some }{,{\\{ edge, edge} \,}{ cases, {here} \\\\\}
EOS

strs.each_line do |s|
  puts s.chomp!
  puts s.unbrace
  puts
end
