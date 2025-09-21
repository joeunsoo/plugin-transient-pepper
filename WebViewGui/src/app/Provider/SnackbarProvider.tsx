'use client';

import { useEffect, useState } from 'react';
import { useSnackbarStore } from '@/store/SnackbarStore';

import Snackbar from '@mui/material/Snackbar';
import IconButton from '@mui/material/IconButton';

import Alert from '@mui/material/Alert';
import { XIcon } from '@phosphor-icons/react';

export default function App() {
  const { refreshCount, open, onClose, message, options } = useSnackbarStore();
  const [count, setCount] = useState(0);

  useEffect(() => {
    setCount(refreshCount);
  }, [refreshCount]);

  if (count !== refreshCount) {
    return null;
  }

  return (
    <Snackbar
      open={open}
      autoHideDuration={3000}
      onClose={(event, reason) => {
        if (reason === 'clickaway') {
          return;
        }

        onClose();
      }}
    >
      <Alert
        // eslint-disable-next-line @typescript-eslint/ban-ts-comment
        // @ts-ignore
        severity={options.variant || 'info'}
        action={
          <IconButton
            size="small"
            color="inherit"
            onClick={onClose}
          >
            <XIcon />
          </IconButton>
        }
      >
        {message}
      </Alert>

    </Snackbar>
  );
}
