'use client';

import { GearSixIcon } from '@phosphor-icons/react';
import * as Juce from 'juce-framework-frontend';
import { ActionIcon, Menu, MenuDivider, MenuDropdown, MenuItem, MenuTarget } from '@mantine/core';
import { CompanyWebsite } from '@/define';
import { useAboutStore } from '@/store/AboutStore';
import { useActivateStore } from '@/store/ActivateStore';
import Scale from './Scale';

const visitWebsite = Juce.getNativeFunction('visitWebsite');

export default function Page() {
  const { open: setAboutOpen } = useAboutStore();
  const { open: setActivateOpen, activate } = useActivateStore();

  return (
    <Menu>
      <MenuTarget>
        <ActionIcon
          size="1.5em"
          variant="transparent"
          sx={{
            color: 'var(--mantine-color-white)',
          }}
        >
          <GearSixIcon size="1.15em" weight="fill" />
        </ActionIcon>
      </MenuTarget>
      <MenuDropdown>
        <Scale />
        <MenuDivider />
        <MenuItem
          onClick={() => {
            visitWebsite(CompanyWebsite);
          }}
        >
          Visit JoEunsoo.com
        </MenuItem>
        <MenuItem
          onClick={() => {
            setAboutOpen();
          }}
        >
          About
        </MenuItem>
        <MenuDivider />
        <MenuItem
          onClick={() => {
            setActivateOpen();
          }}
        >
          {activate ? 'Deactivate' : 'Activate'}
        </MenuItem>
      </MenuDropdown>
    </Menu>
  );
}
