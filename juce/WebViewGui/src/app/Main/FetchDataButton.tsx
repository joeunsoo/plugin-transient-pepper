'use client';

import * as Juce from 'juce-framework-frontend';

import Button from '@mui/material/Button';

import { useSnackbarStore } from '@/src/store/SnackbarStore';

export default function App() {
  const { setOpen } = useSnackbarStore();

  return (
    <Button
      variant="contained"
      sx={{ marginTop: 2 }}
      onClick={() => {
        fetch(Juce.getBackendResourceAddress('data.txt'))
          .then((response) => response.text())
          .then((text) => {
            setOpen('Data fetched: ' + text);

            return null;
          }).catch(null);
      }}
    >
      Fetch
    </Button>
  );
}
