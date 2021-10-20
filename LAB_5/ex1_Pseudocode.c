    if (pid == 0)
    { //child code
      sleep(1); // for a nice output
      char buff[256];
      close(fd[1]);

      while (read(fd[0], buff, sizeof(buff)) > 0)
      {
        printf("Read child = %s\n", buff);
      }
      close(fd[0]); // neccessary
      exit(0);
    }

  else{//parent

      close(fd[0]);

      int i;
      int str_len = 256;
      char str[str_len];
 

      for (i = 1; i < argc; i++)
      {
        //Gửi từng đối số argv[i] đi
        close(fd[0]); // neccessary
        write(fd[1], argv[i], strlen(???));
        printf("Parent send %s\n", argv[i]);
      }
      close(fd[1]); // neccessary
      wait(NULL);
    }
  }
