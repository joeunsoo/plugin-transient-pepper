'use client';

import * as Juce from 'juce-framework-frontend';

import { useActivateStore } from '@/store/ActivateStore';
import { useSnackbarStore } from '@/store/SnackbarStore';
import { useEffect, useState } from 'react';
import { Button, rem, Stack, Text } from '@mantine/core';
import { mantineSpace } from '@/define';

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
    }).catch(console.error);
  }, [setActivate]);

  return (
    <Stack
      px={rem(mantineSpace * 4)}
    >
      <Text>{email}</Text>
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
