'use client';

import * as Juce from 'juce-framework-frontend';

import Scale from './Scale';
import { useAboutStore } from '@/store/AboutStore';
import { CompanyWebsite } from '@/define';
import { useActivateStore } from '@/store/ActivateStore';
import { GearSixIcon } from '@phosphor-icons/react';
import { ActionIcon, Menu, MenuDivider, MenuDropdown, MenuItem, MenuTarget } from '@mantine/core';

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
            color: 'var(--mui-palette-common-white)',
          }}
        >
          <GearSixIcon size="1.15em" weight="fill" />
        </ActionIcon>
      </MenuTarget>
      <MenuDropdown
        sx={{
          '& .MuiPaper-root': {
            backgroundColor: 'var(--mui-palette-primary-darker)',
            color: 'var(--mui-palette-common-white)',
            '& .MuiList-root': {
              py: 0,
            },
            '& .MuiMenuItem-root': {
              py: 0,
              minHeight: '2.4em',
              fontSize: 'var(--mui-fontSize-sm)',
            },
            '& .MuiMenuItem-root:hover': {
              backgroundColor: 'var(--mui-palette-primary-darken)',
            },
            '& .MuiDivider-root': {
              borderColor: 'var(--mui-palette-primary-main)',
            },
            '& .MuiListSubheader-root': {
              color: 'var(--mui-palette-text-disabled)',
              fontSize: 'var(--mui-fontSize-xs)',
              pt: 2,
              backgroundColor: 'transparent',
              lineHeight: 1.5,
            },
          }
        }}
      >
        <Scale />
        <MenuDivider />
        <MenuItem onClick={() => { visitWebsite(CompanyWebsite); }}>
          Visit JoEunsoo.com
        </MenuItem>
        <MenuItem onClick={() => { setAboutOpen(); }}>
          About
        </MenuItem>
        <MenuDivider />
        <MenuItem onClick={() => { setActivateOpen(); }}>
          {activate ? 'Deactivate' : 'Activate'}
        </MenuItem>
      </MenuDropdown>
    </Menu>
  );
}
