<?php


$plugin = array(
  'single' => TRUE,
  'title' => t('Join a group'),
  'icon' => 'icon_contact.png',
  'description' => t('Displays a message for users to join a group if they are not part of one..'),
  'category' => t('EF Users'),
);

/**
 * Implements hook_content_type_render().
 */
function ef_users_join_group_content_type_render($subtype, $conf, $panel_args, $context) {
  $memberships = array();
  $wrapper = entity_metadata_wrapper('user', $GLOBALS['user']->uid);
  $og_memberships_active = $wrapper->{'og_membership__' . OG_STATE_ACTIVE}->value();
  foreach ($og_memberships_active as $membership) {
    if ($membership->group_type == 'node') {
      $memberships[] = $membership;
    }
  }
  $og_memberships_pending = $wrapper->{'og_membership__' . OG_STATE_PENDING}->value();
  foreach ($og_memberships_pending as $membership) {
    if ($membership->group_type == 'node') {
      $memberships[] = $membership;
    }
  }

  // If the user has active or pending memberships, we're done here.
  if (!empty($memberships)) {
    return NULL;
  }

  $block = new stdClass();
  $block->title = t('Find your class');
  $block->content = drupal_get_form('ef_users_join_group_pane_form');
  return $block;
}

/**
 * Returns an edit form for custom type settings.
 */
function ef_users_join_group_content_type_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}
