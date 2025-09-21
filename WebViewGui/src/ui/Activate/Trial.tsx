'use client';

import dayjs from 'dayjs';
import { useEffect, useState } from 'react';
import * as Juce from 'juce-framework-frontend';
import { Button } from '@mantine/core';
import { useActivateStore } from '@/store/ActivateStore';
import { useSnackbarStore } from '@/store/SnackbarStore';

const startTrial = Juce.getNativeFunction('startTrial');
const getTrial = Juce.getNativeFunction('getTrial');

export default function LoginForm() {
  const { setTrial, close } = useActivateStore();
  const { enqueueSnackbar } = useSnackbarStore();
  const [isTrial, setIsTrial] = useState<boolean>(false);
  const [trialDays, setTrialDays] = useState<number>(0);
  const [isEnded, setIsEnded] = useState<boolean>(false);

  useEffect(() => {
    getTrial()
      // eslint-disable-next-line @typescript-eslint/ban-ts-comment
      // @ts-ignore
      .then((result: number) => {
        if (result > 0) {
          setIsTrial(true);
        } else {
          setIsTrial(false);
        }
        const now = dayjs();
        const end = dayjs(result).add(30, 'day');
        if (result > 0 && now.isAfter(end)) {
          setIsEnded(true);

          return null;
        }
        setIsEnded(false);
        const diffMs = end.diff(now); // end - now (밀리초)
        const diffDays = Math.ceil(diffMs / (1000 * 60 * 60 * 24));

        setTrialDays(diffDays);

        return null;
      })
      // eslint-disable-next-line no-console
      .catch(console.error);
  }, []);

  let message = 'Start Trial (30 days)';
  if (isEnded) {
    message = 'Trial Ended';
  } else if (isTrial) {
    message = `Continue Trial (${trialDays} days remaining)`;
  }

  return (
    <Button
      disabled={isEnded}
      onClick={() => {
        if (isTrial) {
          close();
        } else {
          startTrial()
            // eslint-disable-next-line @typescript-eslint/ban-ts-comment
            // @ts-ignore
            .then((result: number) => {
              setTrial(result);
              close();
              enqueueSnackbar('Trial Start', { variant: 'success' });

              return null;
            })
            // eslint-disable-next-line no-console
            .catch(console.error);
        }
      }}
      variant="outline"
      sx={{
        width: '100%',
        color: !isEnded ? 'var(--mantine-color-primary-2)' : 'var(--mantine-color-primary-5)',
      }}
    >
      {message}
    </Button>
  );
}
