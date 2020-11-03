# About these files

## PNG files

bas*.png and z0*.png files are from [The "official" test-suite for PNG](http://www.schaik.com/pngsuite2011/pngsuite.html).

## TXT files

For reading tests, `testProg` compares read from each PNG file data with simple ASCII raw data in corresponding png.txt file. These txt files are generated using stored in create_txt.sci scilab script. To avoid using scilab at build time, these txt files are versionned in git repository.

If you want to generate these txt files, download scilab at [scilab.org](https://www.scilab.org). Then, in Scilab GUI, browse to `test` directory and type:

``` scilab
exec('create_txt.sci', -1)
create_txt
```

Or if you want to do it in a shell (of course, you have to deal with PATH and working directory):

``` sh
scilab -e "exec('./create_txt.sci', -1); create_txt;" -nwni -quit
```
