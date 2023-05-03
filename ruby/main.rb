puts "Hello World"

x = 16
y = 5
z = x.to_i + y.to_i
puts(z)

names = ["Bob", "Kevin", "Alex", "George"]

names.each do |name|
  puts name += "!"
end
