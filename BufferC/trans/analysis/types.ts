module types

// type analysis rules for BufferC

type rules // types

	Void()   : Void()
	Int()    : Int()
	Buffer() : Buffer()
	Bool()   : Bool()
	Char()   : Char()
	FILE()   : FILE()
	
type rules // constants

	Decimal(val) : Int()	
	True()       : Bool()
	False()      : Bool()
	Char(val)    : Char()
	String(val)  : Buffer()
	Null()       : Buffer()
	
type rules // variables

  Param(t, Decl(Identifier(name))): ty
  where t : ty
 
  Var(Identifier(x)) : t
  where definition of x : t
  
  DeclInit(t, Decl(Identifier(x)), e) :-
  where e : e_ty
    and t : ty
    and e_ty == ty
        else error $[[ty] expected] on e
 
type rules // operators 	

  CommaExp(e) : t
  where e : t

	Addition(e1, e2)
  + Subtraction(e1, e2)
  + Multiplication(e1, e2)
  + Division(e1, e2) 
  : Int()
	where e1: ty1
		and e2: ty2
		and ty1 == Int()
			  else error "int expected" on e1
		and ty2 == Int()
			  else error "int expected" on e2

	DecrementPostfix(e)
  + IncrementPostfix(e) : ty
  	where e: ty
  	  and	ty == Int()
  		    else error "int expected" on e
  		
	GreaterThan(e1, e2)
  + GreaterThanEqual(e1, e2)
  + Equal(e1, e2)
  + Inequal(e1, e2)
  + LessThan(e1, e2)
  + LessThanEqual(e1, e2) : Bool()
	where e1: ty1
		and e2: ty2
		and ty1 == ty2
			  else error "types not compatible" on e2
  					
  Or(e1, e2)
  + And(e1, e2) : Bool()
  where e1: Bool()
  			else error "bool expected" on e1
    and e2: Bool()	
  			else error "bool expected" on e2
  			  
	Not(e): Bool()
  where e: Bool()
  			else error "bool expected" on e
  			 
type rules // function calls

	e@FunctionCall(Identifier(name), es): ty
	where definition of name: (ty, tys)
	  and es : tys_es
	  and tys == tys_es
	      else error "argument types not compatible" on e
  			 
type rules // buffer operations

	FunctionCall(Create(), [e]): Buffer()
	where e : Int()
	      else error "int expected" on e
  			 
	FunctionCall(Print(), [e]) : Void()
	where e : Buffer()
	      else error "buffer expected" on e
  
  //deprecated. See printf.str for new type rule	 
  /*FunctionCall(PrintF(), [e1, e2]) : Void()
	where e1 : Buffer()
	      else error "buffer expected" on e1
    and e2 : Buffer()
	      else error "buffer expected" on e2 
  */			 
	FunctionCall(Fopen(), [e1, e2]) : FILE()
	where e1 : Buffer()
	      else error "buffer expected" on e1
    and e2 : Buffer()
	      else error "buffer expected" on e2 
  			 
	FunctionCall(Fread(), [e1, e2]) : Void()
	where e1 : Buffer()
	      else error "buffer expected" on e1
    and e2 : FILE()
	      else error "buffer expected" on e2
	            
type rules // array access

  Field(e, Length()): Int()
  where e : Buffer()
        else error "buffer expected" on e

  ArrayField(e1, e2) : Char()
  where e1 : Buffer()
  	    else error "buffer expected" on e1
  	and e2 : Int()
  	    else error "int expected" on e2
  
  Assign(ArrayField(e1, e2), Assign(), e3) : Char()
  where e1 : Buffer()
  	    else error "buffer expected" on e1
  	and e2 : Int()
  	    else error "int expected" on e2
  	and e3 : Char()
  	    else error "char expected" on e3
  	    
  Assign(Var(Identifier(x)), Assign(), e) : ty
  where definition of x : ty
    and e : ty_e
    and ty_e == ty
        else error $[[ty] expected] on e
        
type rules // statements

  If(e, stm) 
  + While(e, stm) 
  + DoWhile(stm, e) :-
  where e : Bool()
  			else error "bool expected" on e
  			
  IfElse(e, stm1, stm2) :-
  where e : Bool()
  			else error "bool expected" on e

  ForDec(stm1, Some(e), stm2, stm3) :-
  where e : Bool()
  			else error "bool expected" on e
  			
  For(stm1, Some(e), stm2, stm3) :-
  where e : Bool()
  			else error "bool expected" on e
  			
  Exit(Some(e)) :-
  where e : Int()
        else error "int expected" on e
        