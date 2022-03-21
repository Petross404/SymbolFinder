In `Drivers` directory there is the source code that wraps `QProcess`. The latter executes `nm` and `scanelf` to search
for symbols in libraries. The `IDriver` class is abstract and it's solely purpose is to provide a shared interface for
the derived, driver-specific classes.


					      ______________________________
					     |	  Inheritance Diagram:	    |
					      ------------------------------
```

						 -----------------------
						|	QProcess	|
						 _______________________

							   ^
							   |
							   |

					 ---------------------------------------
					|  Process::IDriver : public QProcess 	|	(Abstract class, declares API, signals etc.)
					 _______________________________________

						 	   ^
						 	   |
						 	   |

					 ---------------------------------------
					|    Driver : public Process::IDriver	|	(This is the class we use and defines most of our functions.
					 _______________________________________

					 		   ^
							  / \
							 /   \
							/     \
						       /       \
						      /		\
						     /		 \
						    /		  \
						   /		   \
						  /		    \
						 /		     \
						/		      \
					       /		       \
					      /				\
					     /				 \
					    /				  \
					   /				   \
					  /				    \
					 /				     \
					/				      \
			  --------------------------------   -------------------------------------
			 |    NmDriver : public Driver    | |    ScanelfDriver : public Driver    |
			  ________________________________   _____________________________________

					^					^
					|					|

			`NmDriver` overrides some nm-specific	`ScanelfDriver` overrides some other
			functions, like different nm-arguments	functions, specific to scanelf and it's
			etc.					arguments.
```
