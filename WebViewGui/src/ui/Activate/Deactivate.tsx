'use client';

import { useEffect, useState } from 'react';
import * as Juce from 'juce-framework-frontend';
import { Button, rem, Stack, Text } from '@mantine/core';
import { mantineSpace } from '@/define';
import { useActivateStore } from '@/store/ActivateStore';
import { useSnackbarStore } from '@/store/SnackbarStore';

const getActivate = Juce.getNativeFunction('getActivate');
const setDeactivate = Juce.getNativeFunction('setActivate');

export default function App() {
  const { setActivate } = useActivateStore();
  const { enqueueSnackbar } = useSnackbarStore();
  const [email, setEmail] = useState<string>();

  useEffect(() => {
    getActivate()
      // eslint-disable-next-line @typescript-eslint/ban-ts-comment
      // @ts-ignore
      // eslint-disable-next-line @typescript-eslint/no-explicit-any
      .then((result: any) => {
        setEmail(result.activate);

        return null;
      })
      // eslint-disable-next-line no-console
      .catch(console.error);
  }, [setActivate]);

  return (
    <Stack gap={rem(mantineSpace * 4)}>
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
