{测试常量变量说明}

const m = 'm', e = 'e', I = 'me',{测试点0 1：常量只能是单个字符 错误} 
	length = 20, high = -10, time = +15,{测试点02：常量可以带符号 正确}
	h = '-', {测试点0 3：常量字符必须是字母 错误}
	we := 15; {测试点0 4：常量定义要用= 错误}
const ha = 0; {测试点0 5：const只能出现一次}
var i, j : integer;
    p, q : char;
	tr : array[20] of integer;
	re : array[20] of char;
	ew : array[j] of char;{测试点0 6：数组大小必须确定 错误}
	nu : array[length] of integer;{测试点0 7：数组大小要用无符号整数 错误}
	sa : array[012] of char; {测试点0 8：无符号整数可以用0开头 正确}
var hi = 0;{测试点0 9：var只能出现一次}

procedure test1(){ 测试标识符 }
  var a, b123 : char;
	e : char;
	1e : integer; {测试1 1：数字不能在标识符里开头 错误}
	_ab : integer;{测试1 2：_不能用在标识符里 错误}
  const ab = 15; {测试0 10：常量变量定义的顺序不能乱 错误}
  begin
    e := 'f';
  end
  
procegure test2(var a, b : integer) { 测试符号表 }
  const m = 'i', m = 'o';{测试点2 1：重复定义常量 错误}
  var i : char;
	j : integer;
	a, b : integer;
	c, d, i : integer;{测试点2 2：重复定义变量 错误}
  begin
    write(m);{测试2 3：测试本层常量与外层常量能否分辨 应该输出i}
	write(e);{测试2 4：测试外层常量与平级其它层常量能否分辨 应该输出e}
	i := 'i';
	write(i);
	j := 1;
	write(j);
  end
procedure test3{ 测试赋值语句 }
  var i : integer;
  function xtest : integer
    const x = 10;
	var a, b : integer;
      c, d : char;
	  nu : array[10] of integer;
	begin
	  a := 1;
	  b := 'a'; {测试3 1：char赋值给integer 错误}
	  b := 2;
	  a := a + b;
	  c := 'g';
	  d := 4;{测试3 2：integer赋值给char 错误}
      nu[0] := 4;
	  nu[1] := 'a'; {测试3 3： char赋值给integer数组 错误}
	  xtest := 12;
	  xtext := '1'; {测试3 4：char赋值给integer函数 错误}
	  x := 5;{测试3 5： 尝试为常量赋值 错误}
	  test2 := 4;{测试3 6：尝试为过程赋值 错误}
	end
  begin
    i := xtest;
	write(i);{测试3 7：为函数赋值 输出12}
  end
  
procedure test4(){ 测试函数调用 }
  var a : char;
    i : integer;
  function xtest :integer;
    var i : integer;
    begin
	  i := 1;
	  xtest := i;
	end;
  function ytest ( i : integer; var a : char) : char;
    var j : integer;
	  b : char;
    begin
	  j := 0;
	  b := 'b';
	  if j < i then
        begin
		  i := i - 1;
		  write(b);
		  b := ytest(i, a);
		  ytest := b;
		end
	  else
	    ytest := a;
	end;
  begin
    i := 3;
	a := 'a';
    write(xtest(i));{测试4 1：函数参数表少 错误}
	write(xtest);{测试4 2：输出1}
	write(ytest); {测试4 3：函数参数表多 错误}
	write(ytest(a, i));{测试4 4：函数参数变类型不符 错误}
	write(ytest(i, a));{测试4 5：输出i次'b'，最后输出a}
  end
  
procedure test5(){ 测试条件语句 }
  var a, b, c, d : integer;
  begin
    a := 0;
	b := 1;
	
    if a < b then a := a + 1; write(a); {测试点5 1：小于分支 输出1}
	if a = b then a := a + 1; write(a); {测试点5 2：等于分支 输出2}
	if a > b then a := a + 1; write(a); {测试点5 3：大于分支 输出3}
	if b <= a then a := a + 1; write(a); {测试点5 4：小于等于分支 输出4}
	if a >= b then a := a + 1; write(a); {测试点5 5：大于等于分支 输出5}
	if a <> b then a := a + 1; write(a); {测试点5 6：不等于分支 输出6}
	
	if a < b then a := a - 1; else a := a + 1; write(a); {测试5 7：小于不分支 输出7}
	if a = b then a := a - 1; else a := a + 1; write(a); {测试5 8：等于不分支 输出8}
	if b > a then a := a - 1; else a := a + 1; write(a); {测试5 9：大于不分支 输出9}
	if a <= b then a := a - 1; else a := a + 1; write(a); {测试5 10：小于等于不分支 输出10}
	if b >= a then a := a - 1; else a := a + 1; b := a; write(a); {测试5 11：大于等于不分支 输出11}
	if a <> b then a := a - 1; else a := a + 1; write(a); {测试5 12：不等于不分支 输出12}
	
	if a then ; { 测试5 13：条件不能为变量 出错}
	if a + b then ; {测试5 14：条件不能为表达式 出错}
	if 0 then ; {测试5 14：条件不能为常量 出错}
  end
  
procedure test6(){ 测试case语句 }
  var a, b : integer;
  begin
    b := 1;
	for a := 1 to 3 do begin
      case a of
        2 : b := 3;
		3 : b := 1;
		1 : b := 2;
		0 : b := 0;
	  end
	  write(b); {测试6 1：测试case的各种情况，输出顺序为2 3 1}
	end  
  end
  
procedure test7(){ 测试for语句 }
  var a, b : integer
  begin
    a := -1;
	b := 2;
    for a := a + b to 3 do
	begin
      write(a);
	end
	{测试7 1：顺序输出1 2 3 }
	for a := 3 downto 3 - b do
	begin
	  write(a);
	end
	{测试7 2：顺序输出3 2 1 }
  end
  
procedure test8(var a : interger; b : integer){ 测试过程调用 }
  var i, j : integer;
  begin
	test7(i);{测试8 1：调用参数表错误}
	test7;{测试8 2：调用过程 输出1 2 3 3 2 1 }
    if a >= b then
    begin
      a := a - 1;
	  b := b + 1;
	  i := a;
	  j := b;
	  test8;{测试8 3：调用参数表错误}
	  test8(i);{测试8 4：调用参数表错误}
      test8(i, j);{测试8 5：递归调用过程输出两个nice. }
	  if i = a then write("nice.");
	  if j <> b then write("nice.")
	  {递归调用过程次数为a-b次}
	end
  end
  
procedure test9(){ 测试读语句 }
  var a, b : char;
    i, j : integer;
  begin
    read(a); write(a);{测试9 1：测试读字符}
    read(a, b); write(a); write(b);{测试9 2：测试读多个字符}
    read(i); write(i);{测试9 3：读整数}
    read(i, j); write(i); write(j);{测试9 4：读多个整数}
    read(i, a); write(i); write(a);{测试9 5：测试读不同类型}
  end
  
procedure test10(){ 测试写语句 }
  var a : char;
    i, j : integer;
  begin
    a := 'a';
	i := 1;
	j := 5;
	write("fF~!$%^[]&\/ _{}()|");{测试10 1：测试输出字符串}
	write("	");{测试10 2：这是一个Tab符 错误}
	write(i);
	write(a);{测试10 3：测试正常输出}
	write(i + j);{测试10 4：测试表达式输出}
	write("asd", i);{测试10 5：测试字符串表达式一起输出}
  end
procedure test11(){ 测试表达式 }
  const c = 'c', x = 1;
  var a, b : char;
    i, j, p, q : integer;
  begin
    a := 'a';
	b := 'b';
	i := 3;
	j := 6;
	p := -i; write(p); {测试11 1：输出-3}
	q := +j; write(q); {测试11 2：输出6}
	i := p + q; write(i); {测试11 3：输出3}
    j := p - q; write(j); {测试11 4：输出-9}
	p := i * j; write(p); {测试11 5：输出-27}
	q := i / j; write(q); {测试11 6：输出0}
	i := a + j; write(i); {测试11 7：输出100}
	i := -i - j * p + q / i; write(i);{测试11 8：输出-127}
  end

procedure test12(){ 测试数组 }
  const a = 3; 
  var i, j : integer;
    nu : array[10] of integer;
    ch : array[10] of char;
  function xtest : integer;
  begin
    ch[0] := 'a';{测试12 1：数组从0开始}
	nu[10] := 10;{测试12 2：数组边界检查 错误}
	i := 1;
	nu[1] := i;{测试12 3：表达式赋值}
	j := 2;
	nu[j] := 2;{测试12 4：表达式作下标}
	ch[a] := '2';{测试12 5：常量作下标}
	nu[3] := '3';{测试12 6：类型不匹配 错误}
	nu[xtest] := 1;{测试12 7：函数名作下标 错误}
	nu[test] := 1;{测试12 8：过程名作下标 错误}
  end
begin
  test1;
  test2;
  test3;
  test4;
  test5;
  test6;
  test7;
  test8;
  test9;
  test10;
  test11;
  test12;
end.