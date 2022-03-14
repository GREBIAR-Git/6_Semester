var x = parseInt(process.argv[2]);
console.log('X = ' + x);
var result = '';
while (x > 0)
{
  result += (x % 10).toString();
  x = Math.floor(x / 10);
}
var i = result.length - 1;
while (i >= 0)
{
  console.log(result[i]);
  i -= 1;
}


function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
