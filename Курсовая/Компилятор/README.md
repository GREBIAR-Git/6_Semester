# Описание

Компилятор для подмножества императивного языка Python. Реализует стадии лексического анализа, синтаксического анализа с построением абстрактного синтаксического дерева.

# Виды отлавлеемых ошибок
* Error - incorrect number of tabs(a lot of tabs) - слишком много табов;
* Error - incorrect number of tabs(small number of tabs) - слишком мало табов;
* Error - the difference in the number of opening brackets to the closing ones: - не хватает закрывающихся скобок;
* Error - missing opening parenthesis before - отсутсвует открывающаяся скобка;

# Сценарий использования

## Входной файл

   ```py
_ = 2
_f = 4
class f():
	width = 1;
	h = 2;
	def tf(dsf,d,f,printf):
		dsf = 4+d.h+f+printf
		return 1
	c = input();
d = [2,f]
input();
def tf(dsf,d,f,f):
	kdfff = 4+f.h+ff+printf
	return f.r
while 4<6:
	print(d[3])
	print(kdfff+fdsfsd)
	while 4<6:
		print(d[3])
		print(kdfff+fdsfsd)
		input()
f = input()
if (k > (35+(4)>3) or rte) and fr:
	print(2+4*7)
	print(3)
else:
	fdsf= (4+54435*342)
x = 3
y = 4
z = x + y
f = 5.3
test = true

if (test):
	c = input()
	input()

sd.width = 3
f = tf(a[4],2,3)
for rt in er:
	input()
   ```
## Вывод лексического анализатора
```console
Lexical error on the line 4 - unreserved character: ;
Lexical error on the line 5 - unreserved character: ;
Lexical error on the line 9 - unreserved character: ;
Lexical error on the line 11 - unreserved character: ;

tokens:
#0 : Variable - [ _  ]
#1 : Assignment - [ = ]
#2 : Number - [ 2 ]
#3 : Delimiter - [ \n ]
#4 : Variable - [ _f ]
#5 : Assignment - [ = ]
#6 : Number - [ 4 ]
#7 : Delimiter - [ \n ]
#8 : Class - [ class ]
#9 : Variable - [ f ]
#10 : Open Bracket - [ ( ]
#11 : Close Bracket - [ ) ]
#12 : Double Dot - [ : ]
#13 : Delimiter - [ \n ]
#14 : Tab - [    ]
#15 : Variable - [ width ]
#16 : Assignment - [ = ]
#17 : Number - [ 1 ]
#18 : Delimiter - [ \n ]
#19 : Tab - [    ]
#20 : Variable - [ h ]
#21 : Assignment - [ = ]
#22 : Number - [ 2 ]
#23 : Delimiter - [ \n ]
#24 : Tab - [    ]
#25 : Def - [ def ]
#26 : Variable - [ tf ]
#27 : Open Bracket - [ ( ]
#28 : Variable - [ dsf ]
#29 : Comma - [ , ]
#30 : Variable - [ d ]
#31 : Comma - [ , ]
#32 : Variable - [ f ]
#33 : Comma - [ , ]
#34 : Variable - [ printf ]
#35 : Close Bracket - [ ) ]
#36 : Double Dot - [ : ]
#37 : Delimiter - [ \n ]
#38 : Tab - [    ]
#39 : Tab - [    ]
#40 : Variable - [ dsf ]
#41 : Assignment - [ = ]
#42 : Number - [ 4 ]
#43 : MathSign - [ + ]
#44 : Variable - [ d ]
#45 : Dot - [ . ]
#46 : Variable - [ h ]
#47 : MathSign - [ + ]
#48 : Variable - [ f ]
#49 : MathSign - [ + ]
#50 : Variable - [ printf ]
#51 : Delimiter - [ \n ]
#52 : Tab - [    ]
#53 : Tab - [    ]
#54 : Return - [ return ]
#55 : Number - [ 1 ]
#56 : Delimiter - [ \n ]
#57 : Tab - [    ]
#58 : Variable - [ c ]
#59 : Assignment - [ = ]
#60 : Input - [ input ]
#61 : Open Bracket - [ ( ]
#62 : Close Bracket - [ ) ]
#63 : Delimiter - [ \n ]
#64 : Variable - [ d ]
#65 : Assignment - [ = ]
#66 : Open Braces - [ [ ]
#67 : Number - [ 2 ]
#68 : Comma - [ , ]
#69 : Variable - [ f ]
#70 : Close Braces - [ ] ]
#71 : Delimiter - [ \n ]
#72 : Input - [ input ]
#73 : Open Bracket - [ ( ]
#74 : Close Bracket - [ ) ]
#75 : Delimiter - [ \n ]
#76 : Def - [ def ]
#77 : Variable - [ tf ]
#78 : Open Bracket - [ ( ]
#79 : Variable - [ dsf ]
#80 : Comma - [ , ]
#81 : Variable - [ d ]
#82 : Comma - [ , ]
#83 : Variable - [ f ]
#84 : Comma - [ , ]
#85 : Variable - [ f ]
#86 : Close Bracket - [ ) ]
#87 : Double Dot - [ : ]
#88 : Delimiter - [ \n ]
#89 : Tab - [    ]
#90 : Variable - [ kdfff ]
#91 : Assignment - [ = ]
#92 : Number - [ 4 ]
#93 : MathSign - [ + ]
#94 : Variable - [ f ]
#95 : Dot - [ . ]
#96 : Variable - [ h ]
#97 : MathSign - [ + ]
#98 : Variable - [ ff ]
#99 : MathSign - [ + ]
#100 : Variable - [ printf ]
#101 : Delimiter - [ \n ]
#102 : Tab - [   ]
#103 : Return - [ return ]
#104 : Variable - [ f ]
#105 : Dot - [ . ]
#106 : Variable - [ r ]
#107 : Delimiter - [ \n ]
#108 : While - [ while ]
#109 : Number - [ 4 ]
#110 : Comparison - [ < ]
#111 : Number - [ 6 ]
#112 : Double Dot - [ : ]
#113 : Delimiter - [ \n ]
#114 : Tab - [   ]
#115 : Output - [ print ]
#116 : Open Bracket - [ ( ]
#117 : Variable - [ d ]
#118 : Open Braces - [ [ ]
#119 : Number - [ 3 ]
#120 : Close Braces - [ ] ]
#121 : Close Bracket - [ ) ]
#122 : Delimiter - [ \n ]
#123 : Tab - [   ]
#124 : Output - [ print ]
#125 : Open Bracket - [ ( ]
#126 : Variable - [ kdfff ]
#127 : MathSign - [ + ]
#128 : Variable - [ fdsfsd ]
#129 : Close Bracket - [ ) ]
#130 : Delimiter - [ \n ]
#131 : Tab - [   ]
#132 : While - [ while ]
#133 : Number - [ 4 ]
#134 : Comparison - [ < ]
#135 : Number - [ 6 ]
#136 : Double Dot - [ : ]
#137 : Delimiter - [ \n ]
#138 : Tab - [   ]
#139 : Tab - [   ]
#140 : Output - [ print ]
#141 : Open Bracket - [ ( ]
#142 : Variable - [ d ]
#143 : Open Braces - [ [ ]
#144 : Number - [ 3 ]
#145 : Close Braces - [ ] ]
#146 : Close Bracket - [ ) ]
#147 : Delimiter - [ \n ]
#148 : Tab - [   ]
#149 : Tab - [   ]
#150 : Output - [ print ]
#151 : Open Bracket - [ ( ]
#152 : Variable - [ kdfff ]
#153 : MathSign - [ + ]
#154 : Variable - [ fdsfsd ]
#155 : Close Bracket - [ ) ]
#156 : Delimiter - [ \n ]
#157 : Tab - [   ]
#158 : Tab - [   ]
#159 : Input - [ input ]
#160 : Open Bracket - [ ( ]
#161 : Close Bracket - [ ) ]
#162 : Delimiter - [ \n ]
#163 : Variable - [ f ]
#164 : Assignment - [ = ]
#165 : Input - [ input ]
#166 : Open Bracket - [ ( ]
#167 : Close Bracket - [ ) ]
#168 : Delimiter - [ \n ]
#169 : If - [ if ]
#170 : Open Bracket - [ ( ]
#171 : Variable - [ k ]
#172 : Comparison - [ > ]
#173 : Open Bracket - [ ( ]
#174 : Number - [ 35 ]
#175 : MathSign - [ + ]
#176 : Open Bracket - [ ( ]
#177 : Number - [ 4 ]
#178 : Close Bracket - [ ) ]
#179 : Comparison - [ > ]
#180 : Number - [ 3 ]
#181 : Close Bracket - [ ) ]
#182 : Logical - [ or ]
#183 : Variable - [ rte ]
#184 : Close Bracket - [ ) ]
#185 : Logical - [ and ]
#186 : Variable - [ fr ]
#187 : Double Dot - [ : ]
#188 : Delimiter - [ \n ]
#189 : Tab - [   ]
#190 : Output - [ print ]
#191 : Open Bracket - [ ( ]
#192 : Number - [ 2 ]
#193 : MathSign - [ + ]
#194 : Number - [ 4 ]
#195 : MathSign - [ * ]
#196 : Number - [ 7 ]
#197 : Close Bracket - [ ) ]
#198 : Delimiter - [ \n ]
#199 : Tab - [   ]
#200 : Output - [ print ]
#201 : Open Bracket - [ ( ]
#202 : Number - [ 3 ]
#203 : Close Bracket - [ ) ]
#204 : Delimiter - [ \n ]
#205 : Else: - [ else ]
#206 : Double Dot - [ : ]
#207 : Delimiter - [ \n ]
#208 : Tab - [   ]
#209 : Variable - [ fdsf ]
#210 : Assignment - [ = ]
#211 : Open Bracket - [ ( ]
#212 : Number - [ 4 ]
#213 : MathSign - [ + ]
#214 : Number - [ 54435 ]
#215 : MathSign - [ * ]
#216 : Number - [ 342 ]
#217 : Close Bracket - [ ) ]
#218 : Delimiter - [ \n ]
#219 : Variable - [ x ]
#220 : Assignment - [ = ]
#221 : Number - [ 3 ]
#222 : Delimiter - [ \n ]
#223 : Variable - [ y ]
#224 : Assignment - [ = ]
#225 : Number - [ 4 ]
#226 : Delimiter - [ \n ]
#227 : Variable - [ z ]
#228 : Assignment - [ = ]
#229 : Variable - [ x ]
#230 : MathSign - [ + ]
#231 : Variable - [ y ]
#232 : Delimiter - [ \n ]
#233 : Variable - [ f ]
#234 : Assignment - [ = ]
#235 : Number - [ 5.3 ]
#236 : Delimiter - [ \n ]
#237 : Variable - [ test ]
#238 : Assignment - [ = ]
#239 : Bool - [ true ]
#240 : Delimiter - [ \n ]
#241 : Delimiter - [ \n ]
#242 : If - [ if ]
#243 : Open Bracket - [ ( ]
#244 : Variable - [ test ]
#245 : Close Bracket - [ ) ]
#246 : Double Dot - [ : ]
#247 : Delimiter - [ \n ]
#248 : Tab - [   ]
#249 : Variable - [ c ]
#250 : Assignment - [ = ]
#251 : Input - [ input ]
#252 : Open Bracket - [ ( ]
#253 : Close Bracket - [ ) ]
#254 : Delimiter - [ \n ]
#255 : Tab - [   ]
#256 : Input - [ input ]
#257 : Open Bracket - [ ( ]
#258 : Close Bracket - [ ) ]
#259 : Delimiter - [ \n ]
#260 : Delimiter - [ \n ]
#261 : Variable - [ sd ]
#262 : Dot - [ . ]
#263 : Variable - [ width ]
#264 : Assignment - [ = ]
#265 : Number - [ 3 ]
#266 : Delimiter - [ \n ]
#267 : Variable - [ f ]
#268 : Assignment - [ = ]
#269 : Variable - [ tf ]
#270 : Open Bracket - [ ( ]
#271 : Variable - [ a ]
#272 : Open Braces - [ [ ]
#273 : Number - [ 4 ]
#274 : Close Braces - [ ] ]
#275 : Comma - [ , ]
#276 : Number - [ 2 ]
#277 : Comma - [ , ]
#278 : Number - [ 3 ]
#279 : Close Bracket - [ ) ]
#280 : Delimiter - [ \n ]
#281 : For - [ for ]
#282 : Variable - [ rt ]
#283 : In - [ in ]
#284 : Variable - [ er ]
#285 : Double Dot - [ : ]
#286 : Delimiter - [ \n ]
#287 : Tab - [   ]
#288 : Input - [ input ]
#289 : Open Bracket - [ ( ]
#290 : Close Bracket - [ ) ]
#291 : Delimiter - [ \n ]
#292 : END - [  ]
end tokens
```
## Вывод синтаксического анализатора с абстрактным синтаксическим деревом
```console
START_PARSER

Successfully (A good program without errors well done)

Tree:

Block
 |---Assignment
      |---Variable - _
      |---Number - 2
 |---Assignment
      |---Variable - _f
      |---Number - 4
 |---Class
      |---Variable - f
      |---Block
           |---Assignment
                |---Variable - width
                |---Number - 1
           |---Assignment
                |---Variable - h
                |---Number - 2
           |---Def
                |---Variable - tf
                |---Params
                     |---Variable - dsf
                     |---Comma
                          |---Variable - d
                          |---Comma
                               |---Variable - f
                               |---Comma
                                    |---Variable - printf
                |---Block
                     |---Assignment
                          |---Variable - dsf
                          |---MathSign - +
                               |---Number - 4
                               |---MathSign - +
                                    |---Variable - d
                                         |---Dot - .
                                         |---Variable - h
                                    |---MathSign - +
                                         |---Variable - f
                                         |---Variable - printf
                     |---Return
                          |---Number - 1
           |---Assignment
                |---Variable - c
                |---Input - input
 |---Assignment
      |---Variable - d
      |---Open Braces
           |---Params
                |---Number - 2
                |---Comma
                     |---Variable - f
           |---Close Braces - ]
 |---Input - input
 |---Def
      |---Variable - tf
      |---Params
           |---Variable - dsf
           |---Comma
                |---Variable - d
                |---Comma
                     |---Variable - f
                     |---Comma
                          |---Variable - f
      |---Block
           |---Assignment
                |---Variable - kdfff
                |---MathSign - +
                     |---Number - 4
                     |---MathSign - +
                          |---Variable - f
                               |---Dot - .
                               |---Variable - h
                          |---MathSign - +
                               |---Variable - ff
                               |---Variable - printf
           |---Return
                |---Variable - f
                     |---Dot - .
                     |---Variable - r
 |---While
      |---LogicalOperation
           |---Number - 4
           |---Comparison - <
                |---Number - 6
      |---Block
           |---Output
                |---Number - 3
           |---Output
                |---MathSign - +
                     |---Variable - kdfff
                     |---Variable - fdsfsd
           |---While
                |---LogicalOperation
                     |---Number - 4
                     |---Comparison - <
                          |---Number - 6
                |---Block
                     |---Output
                          |---Number - 3
                     |---Output
                          |---MathSign - +
                               |---Variable - kdfff
                               |---Variable - fdsfsd
                     |---Input - input
 |---Assignment
      |---Variable - f
      |---Input - input
 |---If
      |---LogicalOperation
           |---Logical - or
                |---Variable - k
                |---Comparison - >
                     |---MathSign - +
                          |---Number - 35
                          |---Number - 4
                     |---Comparison - >
                          |---Number - 3
                |---Logical - and
                     |---Variable - rte
                     |---Variable - fr
      |---Block
           |---Output
                |---MathSign - +
                     |---Number - 2
                     |---MathSign - *
                          |---Number - 4
                          |---Number - 7
           |---Output
                |---Number - 3
 |---Else:
      |---Block
           |---Assignment
                |---Variable - fdsf
                |---MathSign - +
                     |---Number - 4
                     |---MathSign - *
                          |---Number - 54435
                          |---Number - 342
 |---Assignment
      |---Variable - x
      |---Number - 3
 |---Assignment
      |---Variable - y
      |---Number - 4
 |---Assignment
      |---Variable - z
      |---MathSign - +
           |---Variable - x
           |---Variable - y
 |---Assignment
      |---Variable - f
      |---Number - 5.3
 |---Assignment
      |---Variable - test
      |---Bool - true
 |---If
      |---LogicalOperation
           |---Variable - test
      |---Block
           |---Assignment
                |---Variable - c
                |---Input - input
           |---Input - input
 |---Assignment
      |---Variable - sd
           |---Dot - .
           |---Variable - width
      |---Number - 3
 |---Assignment
      |---Variable - f
      |---Variable - tf
      |---Function
           |---Variable - tf
           |---Params
                |---Number - 4
                |---Comma
                     |---Number - 2
                     |---Comma
                          |---Number - 3
 |---For
      |---Variable - rt
      |---Variable - er
      |---Block
           |---Input - input

Tree end;

END_PARSER
```