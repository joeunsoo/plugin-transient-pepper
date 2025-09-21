'use client';

import { useEffect, useState } from 'react';
import { MantineProvider } from '@mantine/core';
import { Notifications } from '@mantine/notifications';
import {
  emotionTransform,
  MantineEmotionProvider,
} from '@mantine/emotion';

import { theme } from '@/mantineTheme';

import '@mantine/core/styles.css';
import '@mantine/notifications/styles.css';

type LayoutProps = {
  children: React.ReactNode,
}

export default function Layout({
  children,
}: LayoutProps) {
  const [mounted, setMounted] = useState(false);

  useEffect(() => setMounted(true), []);

  if (!mounted) return null; // 초기 SSR 렌더링에서 렌더링 막기

  return (
    <MantineEmotionProvider>
      <MantineProvider
        theme={theme}
        forceColorScheme="light"
        stylesTransform={emotionTransform}
      >
        <Notifications />
        {children}
      </MantineProvider>
    </MantineEmotionProvider>
  );
}
