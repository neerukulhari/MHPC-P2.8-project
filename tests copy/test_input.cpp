#include <gtest/gtest.h>
#include "prototypes.h"

TEST(InputTest, TextInput)
{
    /* create a temporary file with some lines */
    FILE* fp = tmpfile();
    fputs("  this is a line with spaces and comments # and more spaces  \n", fp);
    fputs("this is another line without comments  \n", fp);
    rewind(fp);

    /* read the first line and check the result */
    char buf[BLEN];
    int result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "  this is a line with spaces and comments");

    /* read the second line and check the result */
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "this is another line without comments");

    /* close the file */
    fclose(fp);
}

TEST(InputTest, EmptyInput)
{
    /* create an empty file */
    FILE* fp = tmpfile();

    /* read a line and check the result */
    char buf[BLEN];
    int result = get_a_line(fp, buf);
    ASSERT_EQ(result, -1);

    /* close the file */
    fclose(fp);
}


TEST(InputTest, CommentInput)
{
    /* create a temporary file with a comment line */
    FILE* fp = tmpfile();
    fputs("# this is a comment line \n", fp);
    rewind(fp);

    /* read the line and check the result */
    char buf[BLEN];
    int result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "");

    /* close the file */
    fclose(fp);
}


TEST(InputTest, Argon108Input)
{
    /* create a temporary file with a comment line */
    FILE* fp = tmpfile();
    fputs("108               # natoms \n", fp);
    fputs("39.948            # mass in AMU \n", fp);
    fputs("0.2379            # epsilon in kcal/mol \n", fp);
    fputs("3.405             # sigma in angstrom \n", fp);
    fputs("8.5               # rcut in angstrom \n", fp);
    fputs("17.1580           # box length (in angstrom) \n", fp);
    fputs("argon_108.rest    # restart \n", fp);
    fputs("argon_108.xyz     # trajectory \n", fp);
    fputs("argon_108.dat     # energies \n", fp);
    fputs("10000             # nr MD steps \n", fp);
    fputs("5.0               # MD time step (in fs) \n", fp);
    fputs("100               # output print frequency \n", fp);
    rewind(fp);

    /* read the line by line and check the result */
    char buf[BLEN];
    int result = get_a_line(fp, buf);
    
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "108");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "39.948");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "0.2379");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "3.405");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "8.5");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "17.1580");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "argon_108.rest");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "argon_108.xyz");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "argon_108.dat");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "10000");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "5.0");
    result = get_a_line(fp, buf);
    ASSERT_EQ(result, 0);
    ASSERT_STREQ(buf, "100");

    /* close the file */
    fclose(fp);
}
