'use client';

import Stack from '@mui/material/Stack';
import * as Juce from 'juce-framework-frontend';

import { useActivateStore } from '@/store/ActivateStore';
import Button from '@mui/material/Button';
import { useSnackbarStore } from '@/store/SnackbarStore';
import { useEffect, useState } from 'react';
import { Typography } from '@mui/material';

const getActivate = Juce.getNativeFunction('getActivate');
const setDeactivate = Juce.getNativeFunction('setActivate');

export default function App() {
  const { setActivate } = useActivateStore();
  const { enqueueSnackbar } = useSnackbarStore();
  const [email, setEmail] = useState<string>();

  useEffect(() => {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    getActivate().then((result: any) => {
      setEmail(result.activate);

      return null;
    }).catch(null);
  }, [setActivate]);

  return (
    <Stack
      spacing={4}
    >
      <Typography>{email}</Typography>
      <Button
        onClick={() => {
          setActivate(false);
          setDeactivate();
          enqueueSnackbar('Deactivate successful', { variant: 'success' });
        }}
        variant="contained"
        sx={{ width: '100%' }}
      >
        Deactivate
      </Button>
    </Stack>
  );
}
