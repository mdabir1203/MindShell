# Coding rules

## while <br/>
int i = -1; <br/>
while(++i < 5) <br/>
{

}

not approved - Ranja - Max
## index and amount <br/>
index count starting from 0 <br/>
number amount is the true number <br/>
f.e. philos = 3 <br/>
philos[0], philos[1], philos[2] <br/>
not approved - Max <br/>

## Headerfile
- Minishell.h -> always put the functions in the right fileslot <br/>
not approved - Max <br/>

- fileslots in header file sorted in order of Vs code explorer<br/>
not approved - Max <br/>

## comments
- describe what the func does right above it, not in header file (there you can't find a special func then) like<br/>
/**<br/>
*<br/>
*<br/>
**/<br/>
-> hover over the function you can see it -> Max test where to put then , header file or in .c file<br/>
not approved - Max <br/>

## merging
-only merge to main when you version is stable - that anyone can branch from there and start implementing a new feature, not dealing with bugs<br/>
not approved - Max <br/>

## Error Codes
Error codes for every single error? # define ERR_PARSER_MALLOC_INFO 2<br/>
Then in error(int err_code) summarize <br/>
not approved - Max <br/>
