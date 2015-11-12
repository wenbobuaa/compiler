const NU = 123456; {测试常量}
  SP = ' ';
var i : integer;
  a := char;
procedure test(var p : integer; t : char);{过程参数传值与传地址}
  var sw, i, j : integer;
  function xtest1 (var i : integer, j : integer): integer; {函数调用传值与传地址}
  {本函数接受两个整数，计算他们的最大公约数}
    var re, a : integer;
    begin
      if i < j then re := xtest1(j, i) {递归调用}
	  else
	    begin
		  if j = 0 then xtest1 := i
		  else
      		begin
			  a := j;
			  j := i - i / j * j;{求余数}
			  i := a;
			  re := xtext1(i, j){递归调用}
			end
		end
    end;
  procedure xtest2 (var a : integer);
  {本过程接收一个整数然后倒序打印由它开始递增的5个数}
    const N := 5;
    var i : integer;
	  s := array[10] of integer;
	begin
	  for i := 0 to N - 1 do{for语句}
	    begin
		  s[i] := a; {数组}
		  a := a + 1
		end;
	  for i := N - 1 downto 0 do
        begin
		  write(s[i]);
		  write(sp){输出空格}
		end
	end;
  procedure xtest3;
  {本过程输出不常见字符串，常量}
    var ch : char;
	begin
	  ch := 'h';
	  write("~!@#$%^&*()");
	  write(sp);
	  write(NU);
	  write(sp);
	  write("=> ", ch);
	  write(sp)
	end;
  begin
    read(sw);
	case sw of {case语句}
	  1 : begin
			read(i, j);
			write(xtest1(i, j));
			write(sp);
			write(i);
			write(sp);
			write(j);
			write(sp)
		  end;
	  2 : begin
			read(i);
			xtest2(i)
		  end;
	  3 : xtest3;
	  4 : begin
			write(p + t);
			write(sp);
			t := '0';
			write(t);
			write(sp);
		  end
	end
  end;
begin
  a := 'a';
  read(i);
  test(i, a);
  write(i);
  write(sp);
  write(a);
  write(sp)
end.