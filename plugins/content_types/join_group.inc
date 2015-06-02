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
  $memberships = og_get_groups_by_user(NULL, 'node');

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
