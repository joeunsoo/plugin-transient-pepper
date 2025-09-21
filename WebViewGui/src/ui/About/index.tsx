'use client';

import {
  CompanyName,
  GlassSx,
  mantineSpace,
  PluginName
} from '@/define';

import { useAboutStore } from '@/store/AboutStore';
import { usePluginStore } from '@/store/PluginStore';
import { Modal, rem, Stack, Text, Title } from '@mantine/core';

export default function App() {
  const { opened, close } = useAboutStore();
  const { pluginInfo } = usePluginStore();

  return (
    <Modal
      opened={opened}
      onClose={close}
      centered
      withCloseButton={false}
      p={rem(mantineSpace * 4)}
      styles={{
        content: {
          ...GlassSx,
        }
      }}
    >
      <Stack align="center">
        <Title order={4}>
          {PluginName}
        </Title>
        <Text size="sm">
          v{pluginInfo.pluginVersion}
        </Text>
        <Title order={6} pt={rem(mantineSpace * 4)}>
          &copy; {CompanyName}.
        </Title>
      </Stack>
    </Modal>
  );
}
