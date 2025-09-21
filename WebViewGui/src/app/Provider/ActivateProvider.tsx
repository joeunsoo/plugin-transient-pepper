import dayjs from 'dayjs';
import { useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';
import { useActivateStore } from '@/store/ActivateStore';
import Activate from '@/ui/Activate';

const getActivate = Juce.getNativeFunction('getActivate');

export default function App() {
  const { open, setActivate, setTrial } = useActivateStore();

  useEffect(() => {
    getActivate()
      // eslint-disable-next-line @typescript-eslint/ban-ts-comment
      // @ts-ignore
      // eslint-disable-next-line @typescript-eslint/no-explicit-any
      .then((result: any) => {
        const activate = result.activate.length > 0;
        const trial = result.trial;
        if (activate) {
          setActivate(true);
        }
        if (trial > 0) {
          setTrial(trial);
        }

        const now = dayjs();
        const end = dayjs(trial).add(30, 'day');
        const trialEnded = now.isAfter(end); // true = 트라이얼 만료

        if (!activate && (!trial || trialEnded)) {
          open();
        }

        return null;
      })
      // eslint-disable-next-line no-console
      .catch(console.error);
  }, [open, setActivate, setTrial]);

  return <Activate />;
}
