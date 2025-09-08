'use client';

import Snackbar from '@mui/material/Snackbar';
import IconButton from '@mui/material/IconButton';
import CloseIcon from '@mui/icons-material/Close';

import { useSnackbarStore } from '@/src/store/SnackbarStore';

export default function App() {
  const { open, onClose, message } = useSnackbarStore();

  const action = (
    <IconButton
      size="small"
      aria-label="close"
      color="inherit"
      onClick={onClose}
    >
      <CloseIcon fontSize="small" />
    </IconButton>
  );

  return (
    <Snackbar
      open={open}
      autoHideDuration={6000}
      onClose={(event, reason) => {
        if (reason === 'clickaway') {
          return;
        }

        onClose();
      }}
      message={message}
      action={action}
    />
  );
}
