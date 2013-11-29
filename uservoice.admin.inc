<?php

/**
 * Module settings form.
 */
function uservoice_settings($form, &$form_state) {

  $trigger_style_default_value = variable_get('trigger_style', 'icon');

  $form['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#default_value' => variable_get('api_key', NULL),
    '#required' => TRUE,
  );

  $form['mode'] = array(
    '#type' => 'select',
    '#title' => t('Mode'),
    '#options' => array(
        'contact'      => t('Contact'),
        'satisfaction' => t('Satisfaction Rating'),
        'smartvote'    => t('SmartVote'),
     ),
    '#default_value' => variable_get('mode', 'contact'),
  );

  $form['locale'] = array(
    '#title' => t('Locale'),
    '#description' => t('If not supported by UserVoice, the default language is english.'),
    '#default_value' => variable_get('locale', 'EN'),
  );

  if (module_exists('locale')) {
    $form['locale']['#type']    = 'select';
    $form['locale']['#options'] = country_get_list();
  }
  else {
    $form['locale']['#type']        = 'textfield';
    $form['locale']['#description'] = t('Ex: FR, EN, etc.<br/>If not supported by UserVoice, the default language is english.');
  }

  $form['customization'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Customization'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  );

  $form['customization']['accent_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Accent color'),
    '#description' => t('Ex: rgba(68, 141, 214, 0.6), #448dd6, blue'),
    '#default_value' => variable_get('accent_color', '#448dd6'),
  );

  $form['customization']['trigger_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Trigger color'),
    '#description' => t('Ex: rgba(255, 255, 255, 1), #ffffff, white'),
    '#default_value' => variable_get('trigger_color', '#ffffff'),
  );

  $form['customization']['trigger_background_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Trigger background color'),
    '#description' => t('Ex: rgba(46, 49, 51, 0.6), #2e3133, grey'),
    '#default_value' => variable_get('trigger_background_color', 'rgba(46, 49, 51, 0.6)'),
  );

  $form['customization']['trigger_style'] = array(
    '#type' => 'select',
    '#title' => t('Trigger style'),
    '#options' => array(
      'icon' => t('icon'),
      'tab'  => t('tab'),
     ),
    '#default_value' => $trigger_style_default_value,
    '#ajax' => array(
      'callback' => 'uservoice_trigger_style_callback',
      'wrapper' => 'trigger-position-div',
      'method' => 'replace'
    )
  );

  $trigger_style_value = $trigger_style_default_value;

  if (isset($form_state['values']) && isset($form_state['values']['trigger_style'])) {
    $trigger_style_value = $form_state['values']['trigger_style'];
  }

  $trigger_position_options = array(
    'bottom-right' => t('bottom-right'),
    'bottom-left'  => t('bottom-left'),
    'top-left'     => t('top-left'),
    'top-right'    => t('top-right'),
  );

  if ($trigger_style_value == 'tab') {
    $trigger_position_options = array(
      'left'  => t('left'),
      'right' => t('right'),
    );
  }

  $form['customization']['trigger_position'] = array(
    '#type' => 'select',
    '#prefix' => '<div id="trigger-position-div">',
    '#suffix' => '</div>',
    '#title' => t('Trigger position'),
    '#options' => $trigger_position_options,
    '#default_value' => variable_get('trigger_position', 'bottom-right'),
  );

  return system_settings_form($form);
}

function uservoice_trigger_style_callback($form, $form_state) {
  return $form['customization']['trigger_position'];
}
