print 'X = '
x = gets.chomp.to_i
result = ''
while x > 0
  result = result + (x % 10).to_s
  x = x / 10
end
i = result.length - 1
while i >= 0
  puts result[i]
  i = i - 1
end
gets
