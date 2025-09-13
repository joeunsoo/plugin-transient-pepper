'use client';

import * as Juce from 'juce-framework-frontend';

import Button from '@mui/material/Button';

import { useSnackbarStore } from '@/store/SnackbarStore';

export default function App() {
  const { enqueueSnackbar } = useSnackbarStore();

  return (
    <Button
      variant="contained"
      sx={{ marginTop: 2 }}
      onClick={() => {
        fetch(Juce.getBackendResourceAddress('data.txt'))
          .then((response) => response.text())
          .then((text) => {
            enqueueSnackbar('Data fetched: ' + text);

            return null;
          }).catch(null);
      }}
    >
      Fetch
    </Button>
  );
}
