/* gen.c -- Generate pseudorandom numbers. */

/* Examples:

  $ gen 10 
10 real numbers 0 <= X < 1 generated by mpf_urandomb()

  $ gen -f mpz_urandomb 10
10 integers 0 <= X < 2^32 

  $ gen -f mpz_urandomb -z 127 10
10 integers 0 <= X < 2^127

  $ gen -x .9,1 10
10 real numbers 0 <= X < .9

  $ gen -s 1 10
10 real numbers, sequence seeded with 1
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <gmp.h>

int main (argc, argv)
     int argc;
     char *argv[];
{
  const char usage[] =
    "usage: gen [-abhx] [-f func] [-s #] [-z #] n\n" \
    "  n        number of numbers to generate\n" \
    "  -a       ASCII output in radix 10 (default)\n" \
    "  -b       binary output\n" \
    "  -f func  random function, one of\n" \
    "           mpz_urandomb, mpf_urandomb (default), rand, random\n" \
    "  -h       print this text and exit\n" \
    "  -s #     initial seed (default: output from time(3))\n" \
    "  -z #     size in bits of generated integer numbers (0<= X <2^#) \n" \
    "           (default 32)\n" \
    "  -x f,t   exclude all numbers f <= x <= t\n" \
    "";

  unsigned long int f;
  unsigned long int n;
  unsigned long int seed;
  int seed_from_user = 0;
  unsigned int size = 32;
  mpz_t z1;
  mpf_t f1;
  gmp_rand_state s;
  int c, i;
  int ascout = 1, binout = 0;
  double drand;
  long lrand;
  int do_exclude = 0;
  mpf_t f_xf, f_xt;		/* numbers to exclude from sequence */
  char *str_xf, *str_xt;	/* numbers to exclude from sequence */
  enum 
  {
    RFUNC_mpz_urandomb = 0,
    RFUNC_mpf_urandomb,
    RFUNC_rand,
    RFUNC_random,
  } rfunc = RFUNC_mpf_urandomb;
  char *rfunc_str[] =  { "mpz_urandomb", "mpf_urandomb", "rand", "random" };
  gmp_rand_algorithm rand_alg = GMP_RAND_ALG_DEFAULT;

  mpf_init (f_xf); mpf_init (f_xt);

  while ((c = getopt (argc, argv, "abf:hn:s:z:x:")) != -1)
    switch (c)
      {
      case 'a':
	ascout = 1;
	binout = 0;
	break;

      case 'b':
	ascout = 0;
	binout = 1;
	break;

      case 'f':
	rfunc = -1;
	for (f = 0; f < sizeof (rfunc_str) / sizeof (*rfunc_str); f++)
	    if (!strcmp (optarg, rfunc_str[f]))
		rfunc = f;
	if (rfunc == -1)
	  {
	    fputs (usage, stderr);
	    exit (1);
	  }
	break;

      case 's':
	seed = strtoul (optarg, NULL, 10);
	seed_from_user = 1;
	break;

      case 'z':
	size = atoi (optarg);
	if (size < 1)
	  {
	    fprintf (stderr, "gen: bad size argument (-z %u)\n", size);
	    exit (1);
	  }
	break;

      case 'x':			/* exclude */
	str_xf = optarg;
	str_xt = strchr (optarg, ',');
	if (NULL == str_xt)
	  {
	    fprintf (stderr, "gen: bad exclusion parameters: %s\n", optarg);
	    exit (1);
	  }
	*str_xt++ = '\0';
	do_exclude = 1;
	break;

      case 'h':
      case '?':
      default:
	fputs (usage, stderr);
	exit (1);
      }
  argc -= optind;
  argv += optind;

  if (argc < 1)
    {
      fputs (usage, stderr);
      exit (1);
    }

  mpz_init (z1);
  mpf_init (f1);

  if (!seed_from_user)
    seed = (unsigned long int) time (NULL);
  
  /* set seed */
  switch (rfunc)
    {
    case RFUNC_mpz_urandomb:
    case RFUNC_mpf_urandomb:
      mpz_set_ui (z1, seed);
      gmp_rand_init (&s, rand_alg, size, z1);
      break;

    case RFUNC_rand:
      srand (seed);
      break;

    case RFUNC_random:
      /* srandom (seed); */
      srandomdev ();
      break;

    default:
      fprintf (stderr, "gen: random function not implemented\n");
      exit (1);
    }

  /* set up excludes */
  if (do_exclude)
    switch (rfunc)
      {
      case RFUNC_mpf_urandomb:
      
	if (mpf_set_str (f_xf, str_xf, 10) ||
	    mpf_set_str (f_xt, str_xt, 10))
	  {
	    fprintf (stderr, "gen: bad exclusion-from (\"%s\") " \
		     "or exclusion-to (\"%s\") string.  no exclusion done.\n",
		     str_xf, str_xt);
	    do_exclude = 0;
	  }
	break;

      default:
	fprintf (stderr, "gen: exclusion not implemented for chosen " \
		 "randomization function.  all numbers included in sequence.\n");
      }
  
  /* generate and print */
  n = strtoul (argv[0], (char **) NULL, 10);
  for (f = 0; f < n; f++)
    {
      switch (rfunc)
	{
	case RFUNC_mpz_urandomb:
	  mpz_urandomb (z1, &s);
	  if (binout)
	    {
	      /*fwrite ((unsigned int *) z1->_mp_d, 4, 1, stdout);*/
	      fprintf (stderr, "gen: binary output for mpz_urandomb is broken\n");
	      exit (1);
	    }
	  else
	    {
	      mpz_out_str (stdout, 10, z1);
	      puts ("");
	    }
	  
	  break;

	case RFUNC_mpf_urandomb:
	  mpf_urandomb (f1, &s);
	  if (do_exclude)
	    if (mpf_cmp (f1, f_xf) >= 0 && mpf_cmp (f1, f_xt) <= 0)
		break;
	  if (binout)
	    {
	      fprintf (stderr, "gen: binary output for floating point numbers "\
		       "not implemented\n");
	      exit (1);
	    }
	  else
	    {
	      mpf_out_str (stdout, 10, 0, f1);
	      puts ("");
	    }
	  break;

	case RFUNC_rand:
	  i = rand ();
#ifdef FLOAT_OUTPUT
	  if (i)
	    drand = (double) i / (double) RAND_MAX;
	  else
	    drand = 0.0;
	  if (binout)
	    fwrite (&drand, sizeof (drand), 1, stdout);
	  else
	    printf ("%e\n", drand);
#else
	  if (binout)
	    fwrite (&i, sizeof (i), 1, stdout);
	  else
	    printf ("%d\n", i);
#endif
	  break;

	case RFUNC_random:
	  lrand = random ();
	  if (lrand)
	    drand = (double) lrand / (double) 0x7fffffff;
	  else
	    drand = 0;
	  if (binout)
	    fwrite (&drand, sizeof (drand), 1, stdout);
	  else
	    printf ("%e\n", drand);
	  break;

	default:
	  fprintf (stderr, "gen: random function not implemented\n");
	  exit (1);
	}
      
    }

  /* clean up */
  switch (rfunc)
    {
    case RFUNC_mpz_urandomb:
    case RFUNC_mpf_urandomb:
      gmp_rand_clear (&s);
      break;
    default:
      break;
    }
  mpz_clear (z1);
  mpf_clear (f1);
  mpf_clear (f_xf); mpf_clear (f_xt);

  return 0;
}





